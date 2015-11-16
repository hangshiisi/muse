#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pace2.h>
#include <assert.h>

#define PACE2_PA_TAGS_MAX (PACE2_PA_TAGS_CUSTOM_COUNT + PACE2_PA_TAGS_DEFAULT_COUNT)

/* pointer to the initalized memory */
static struct PACE2_global_config config;
static PACE2_module *pace2 = NULL;

static void *my_malloc( u64 size, int thread_ID, void *user_ptr, int scope )
{
    return malloc( size );
}

static void my_free( void *ptr, int thread_ID, void *user_ptr, int scope )
{
    free( ptr );
}

static void *my_realloc( void *ptr, u64 size, int thread_ID, void *user_ptr, int scope )
{
    return realloc( ptr, size );
}

/* initialization function for PACE and hash tables */
static void pace_initialization(void)
{
    pace2_init_default_config(&config);

    config.general.pace2_alloc = my_malloc;
    config.general.pace2_free = my_free;
    config.general.pace2_realloc = my_realloc;
} /* pace_initialization */

static void pace_exit(void)
{
    pace2_exit_module(pace2);
} /* pace_exit */

static PACE2_return_state pace2_write_xml_statement(FILE *tag_xml_file, const char *line, u8 level, u8 new_line)
{
    u16 depth = level * 4;
    fprintf(tag_xml_file, "%*s%s", depth, "", line);

    if (new_line == IPQ_TRUE) {
        fprintf(tag_xml_file, "\n");
    }
    return PACE2_SUCCESS;
}

static PACE2_return_state pace2_print_tags(PACE2_module * const pace2_module, FILE *tag_xml_file)
{
    char tag_id[32];
    u16 tag = 0;

    pace2_write_xml_statement (tag_xml_file, "<tags>", 1, IPQ_TRUE);

    for(; tag < PACE2_PA_TAGS_MAX; ++tag) {
        const char *tag_string = pace2_get_pa_tag_string(pace2_module, tag);
        if (tag_string != NULL && *tag_string != 0) {
            sprintf(tag_id, "<tag id=\"%d\">", tag);
            pace2_write_xml_statement(tag_xml_file, tag_id, 2, IPQ_TRUE);

            pace2_write_xml_statement(tag_xml_file, "<name>", 3, IPQ_FALSE);
            fprintf(tag_xml_file, "%s", tag_string);
            fprintf(tag_xml_file, "</name>\n");

            pace2_write_xml_statement(tag_xml_file, "</tag>", 2, IPQ_TRUE);
        }
    }
    pace2_write_xml_statement (tag_xml_file, "</tags>", 1, IPQ_TRUE);
    return PACE2_SUCCESS;
}

static PACE2_return_state pace2_print_protocols(PACE2_module * const pace2_module, FILE *tag_xml_file)
{
    char group_id[32];
    char main_tag_id[32];
    char tag_id[32];
    const char *str = NULL;
    u16 protocol = 0;
    u16 tag = 0;

    pace2_write_xml_statement (tag_xml_file, "<protocols>", 1, IPQ_TRUE);

    static const char *protocols_long_str[] = { PACE2_PROTOCOLS_LONG_STRS };
    static const char *protocols_short_str[] = { PACE2_PROTOCOLS_SHORT_STRS };
    static const char *protocols_description[] = { PACE2_PROTOCOLS_DESCRIPTIONS };

    for(; protocol < PACE2_PROTOCOL_COUNT; ++protocol) {

        sprintf(group_id, "<protocol id=\"%d\">", protocol );
        pace2_write_xml_statement (tag_xml_file, group_id, 2, IPQ_TRUE);

        pace2_write_xml_statement (tag_xml_file, "<name>", 3, IPQ_FALSE);
        str = protocols_short_str[protocol];
        if (str != NULL) {
            fprintf(tag_xml_file, "%s", str );
        }
        fprintf(tag_xml_file, "</name>\n" );

        pace2_write_xml_statement (tag_xml_file, "<long_name>", 3, IPQ_FALSE);
        str = protocols_long_str[protocol];
        if (str != NULL) {
            fprintf(tag_xml_file, "%s", str );
        }
        fprintf(tag_xml_file, "</long_name>\n" );

        sprintf(main_tag_id, "<main_tag id=\"%d\">", pace2_get_protocol_main_tag(pace2_module, protocol));
        pace2_write_xml_statement (tag_xml_file, main_tag_id, 3, IPQ_FALSE);
        fprintf(tag_xml_file, "%s", pace2_get_protocol_main_tag_string(pace2_module, protocol));
        fprintf(tag_xml_file, "</main_tag>\n");

        pace2_write_xml_statement (tag_xml_file, "<tags>", 3, IPQ_TRUE);
        for(; tag < PACE2_PA_TAGS_MAX; ++tag) {
            if(pace2_protocol_has_tag(pace2_module, protocol, tag)) {
                sprintf(tag_id, "<tag id=\"%d\">", tag);
                pace2_write_xml_statement (tag_xml_file, tag_id, 4, IPQ_FALSE);
                fprintf(tag_xml_file, "%s", pace2_get_pa_tag_string(pace2_module, tag));
                fprintf(tag_xml_file, "</tag>\n");
            }
        }
        pace2_write_xml_statement (tag_xml_file, "</tags>", 3, IPQ_TRUE);

        pace2_write_xml_statement (tag_xml_file, "<description>", 3, IPQ_FALSE);
        str = protocols_description[protocol];
        if (str != NULL) {
            fprintf(tag_xml_file, "%s", str );
        }
        fprintf(tag_xml_file, "</description>\n" );

        pace2_write_xml_statement (tag_xml_file, "</protocol>", 2, IPQ_TRUE);
    }
    pace2_write_xml_statement (tag_xml_file, "</protocols>", 1, IPQ_TRUE);
    return PACE2_SUCCESS;
}

static PACE2_return_state pace2_print_applications(PACE2_module * const pace2_module, FILE *tag_xml_file)
{
    char group_id[32];
    char main_tag_id[32];
    char tag_id[32];
    const char *str = NULL;
    u16 app = 0;
    u16 tag = 0;

    pace2_write_xml_statement (tag_xml_file, "<applications>", 1, IPQ_TRUE);

    static const char *apps_long_str[] = { PACE2_APPLICATIONS_LONG_STRS };
    static const char *apps_short_str[] = { PACE2_APPLICATIONS_SHORT_STRS };

    for(; app < PACE2_APPLICATIONS_COUNT; ++app) {

        sprintf( group_id, "<application id=\"%d\">", app );
        pace2_write_xml_statement (tag_xml_file, group_id, 2, IPQ_TRUE);

        pace2_write_xml_statement (tag_xml_file, "<name>", 3, IPQ_FALSE);
        str = apps_short_str[app];
        if (str != NULL) {
            fprintf(tag_xml_file, "%s", str );
        }
        fprintf(tag_xml_file, "</name>\n" );

        pace2_write_xml_statement (tag_xml_file, "<long_name>", 3, IPQ_FALSE);
        str = apps_long_str[app];
        if (str != NULL) {
            fprintf(tag_xml_file, "%s", str );
        }
        fprintf(tag_xml_file, "</long_name>\n" );

        sprintf(main_tag_id, "<main_tag id=\"%d\">", pace2_get_application_main_tag(pace2_module, app));
        pace2_write_xml_statement (tag_xml_file, main_tag_id, 3, IPQ_FALSE);
        fprintf(tag_xml_file, "%s", pace2_get_application_main_tag_string(pace2_module, app));
        fprintf(tag_xml_file, "</main_tag>\n");

        pace2_write_xml_statement (tag_xml_file, "<tags>", 3, IPQ_TRUE);
        for(; tag < PACE2_PA_TAGS_MAX; ++tag) {
            if(pace2_application_has_tag(pace2_module, app, tag)) {
                sprintf(tag_id, "<tag id=\"%d\">", tag);
                pace2_write_xml_statement (tag_xml_file, tag_id, 4, IPQ_FALSE);
                fprintf(tag_xml_file, "%s", pace2_get_pa_tag_string(pace2_module, tag));
                fprintf(tag_xml_file, "</tag>\n");
            }
        }
        pace2_write_xml_statement (tag_xml_file, "</tags>", 3, IPQ_TRUE);

        pace2_write_xml_statement (tag_xml_file, "</application>", 2, IPQ_TRUE);
    }
    pace2_write_xml_statement (tag_xml_file, "</applications>", 1, IPQ_TRUE);
    return PACE2_SUCCESS;
}

PACE2_return_state pace2_create_pa_tagging(PACE2_module * const pace2_module, const char *filename)
{
    if(pace2_module == NULL || filename == NULL || (strcmp(filename, "") == 0)) {
        return PACE2_PARAM_MISSING;
    }

    FILE *tag_xml_file = fopen(filename, "w");

    if (tag_xml_file == NULL) {
        return PACE2_FAILURE;
    }

    fprintf(tag_xml_file, "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n");
    fprintf(tag_xml_file, "<protocol_information xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"" \
                          " xsi:schemaLocation=\"http://www.ipoque.com/pace2_pa_tagging pace2_pa_tagging.xsd\"" \
                          " xmlns=\"http://www.ipoque.com/pace2_pa_tagging\">\n");

    PACE2_return_state ret = pace2_print_tags (pace2_module, tag_xml_file);
    if (ret != PACE2_SUCCESS) {
        return ret;
    }

    ret = pace2_print_protocols (pace2_module, tag_xml_file);
    if (ret != PACE2_SUCCESS) {
        return ret;
    }

    ret = pace2_print_applications (pace2_module, tag_xml_file);
    if (ret != PACE2_SUCCESS) {
        return ret;
    }

    fprintf(tag_xml_file, "</protocol_information>\n");


    if(fclose(tag_xml_file) == EOF) {
        return PACE2_FAILURE;
    }
    return PACE2_SUCCESS;
}

int main( int argc, char **argv )
{
    /* initialize PACE */
    if(argc < 2) {
        printf("ERROR: Filename parameter missing.\n");
        printf("Usage: $ pace_create_tag_xml example_tagging.xml\n");
        return PACE2_FAILURE;
    }

    pace_initialization();
    config.s3_classification.pa_tags.enabled = IPQ_TRUE;

    int res = (int)pace2_init(&config, &pace2);
    if(res != PACE2_SUCCESS) {
        goto clean_and_exit;
    }
    assert(pace2 != NULL);

    res = (int)pace2_create_pa_tagging( pace2, argv[1] );
    if(res != PACE2_SUCCESS) {
        goto clean_and_exit;
    }

clean_and_exit:
    /* free memory */
    pace_exit();

    if(res != PACE2_SUCCESS) {
        printf("ERROR %d: %s\n", res, pace2_return_state_str(res));
    }
    return res;
} /* main */
