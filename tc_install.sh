#!/bin/bash

# Install TC needed packages. 


if [[ "$USER" != 'root' ]]; then
    echo "Sorry, you need to run this as root"
    exit
fi


if grep -qs "CentOS" "/etc/redhat-release"; then
    echo "CentOS 5 not supported yet"
    exit
fi

if [[ -e /etc/debian_version ]]; then
        OS=debian
        RCLOCAL='/etc/rc.local'
else
        echo "Looks like you aren't running this installer on a Debian, Ubuntu or CentOS system"
        exit
fi

echo "TC Installation starts" 

# Try to get our IP from the system and fallback to the Internet.
# I do this to make the script compatible with NATed servers (lowendspirit.com)
# and to avoid getting an IPv6.
IP=$(ip addr | grep 'inet' | grep -v inet6 | grep -vE '127\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}' | grep -o -E '[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}' | head -1)
if [[ "$IP" = "" ]]; then
    IP=$(wget -qO- ipv4.icanhazip.com)
fi


echo "The IP Address is $IP" 

#enable IP forwarding 
if [[ "$OS" = 'debian' ]]; then
    sed -i 's|#net.ipv4.ip_forward=1|net.ipv4.ip_forward=1|' /etc/sysctl.conf

fi 

# Avoid an unneeded reboot
echo 1 > /proc/sys/net/ipv4/ip_forward
sysctl -p 

# install git 
apt-get install -y git 

# install python dev packages 
apt-get install -y python-pip 
apt-get install -y build-essential python-dev libnetfilter-queue-dev

pip install --upgrade scapy Flask 

pip install --upgrade python-iptables



