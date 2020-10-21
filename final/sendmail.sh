#!/bin/bash

echo "Hey, who would you like to send a mail to?"
read mailaddress
echo "Kindlt enter the mail subject "
read subject
echo "Enter the content of the mail and type enter to send :)"
read content
echo "$content" | mail -s "$subject" $mailaddress