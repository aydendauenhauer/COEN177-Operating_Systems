# Name: Ayden Dauenhauer
# Date: Jan 6, 2025
# Title: Lab1 - Unix/Linux Commands and Basic Shell Programming
# Description: To learn Unix/ Linux, use command line programs, and develop sample shell programs

echo Executing $0
echo $(/bin/ls | wc -l) files
wc -l $(/bin/ls)
echo "HOME="$HOME
echo "USER="$USER
echo "PATH="$PATH
echo "PWD="$PWD
echo "\$\$="$$
user=`whoami`
numusers=`who | wc -l`
echo "Hi $user! There are $numusers users logged on."
if [ $user = "aydendauenhauer" ] #Replace with your own username!
then
  echo "Now you can proceed!"
else
  echo "Check who logged in!"
  exit 1
fi

pi=3.14
response="Yes"
while [ $response != "No" ]
do
  echo "Enter radius of circle: "
  read radius
  area=$(echo "$radius * $radius * $pi" | bc)
  echo "The area of the circle is $area"

  echo "Would you like to repeat for another circle [Yes/No]?"
  read response
done