Instruction for starting:
make
modinfo driver.co
sudo insmod driver.ko value=15
cat /var/log/kern.log
sudo rmmod driver.ko
cat /var/log/kern.log
ls /sys/module/driver/parameters
sudo sh -c "echo 13 > /sys/module/driver/parameters/value"
cat /var/log/kern.log
sudo rmmod driver.ko