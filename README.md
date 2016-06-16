G-WAN++
=======

C++ Web framework for G-WAN application server.

csp/main.cpp is an example of usage

Setup
=======
sudo apt-get install libmysqlclient-dev
sudo apt-get install libtinyxml-dev

wget http://gwan.com/archives/gwan_linux64-bit.tar.bz2
tar -xjf gwan_linux64-bit.tar.bz2
cd gwan_linux64-bit
rm -rf 0.0.0.0:8080/#0.0.0.0/*

git clone git@github.com:punarinta/gwan-pp.git 0.0.0.0:8080/#0.0.0.0
cd 0.0.0.0:8080/#0.0.0.0
cp csp/config/db.cfg.dist csp/config/db.cfg
