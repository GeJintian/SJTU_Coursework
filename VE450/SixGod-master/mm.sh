#!/usr/bin/env bash
sshpass -p "123456" scp -r /tmp/picture/* binyu@20.20.10.106:/mnt/d/picture
#cp -r /tmp/picture/* /home/odroid/camera/picture
rm /tmp/picture/*
#make
./SixGod
#./Stop