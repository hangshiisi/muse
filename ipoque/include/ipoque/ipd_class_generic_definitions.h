/********************************************************************************/
/**
 ** \file       ipd_class_generic_definitions.h
 ** \brief      Generic structure for fields, which every class event structure
 **             contains.
 **/
/********************************************************************************/

#ifndef IPD_CLASS_GENERIC_DEFINITIONS_H_
#define IPD_CLASS_GENERIC_DEFINITIONS_H_

#ifndef __IPOQUE_DECODER_INCLUDE_FILE__
#error please include ipd.h instead of this file
#endif

/**
 * Structur for a generic information for many events (low-level and high-level).
 * It's guaranty that the ID of the event is unique. For all (high-level) class events
 * the generic header is used. For low-level decoder events is it used only by few decoder.
 */
struct ipd_class_generic_header
{
	/** The ID of the event (is unique) */
	u64 id;
};


#endif /* IPD_CLASS_GENERIC_DEFINITIONS_H_ */
