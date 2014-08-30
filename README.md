Liwall
=========

Liwall is a Linux firewall to block websites.

  - Write Ip's in list.txt
  - Compile and insmod the module formed
  - Ip's blocked

Version
----

1.0

Installation
--------------

```sh
git clone git@github.com:nkman/Liwall.git
cd liwall
vim list.txt <Insert the ip's to block with a new line char>
sudo make
sudo insmod firewall.ko
```

Removal
-----------

```sh
sudo rmmod firewall
```

License
----

MIT


**Free Software**
