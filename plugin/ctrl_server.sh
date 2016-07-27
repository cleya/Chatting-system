#!/bin/bash

PATH=$(pwd)	
CONF=${PATH}/conf
BIN=${PATH}/bin
LOG=${PATH}/log

BIN_NAME=udp_serverd



proc_name = $(basename $0)
function Usage()
{
	printf "%s %s\n" "Usage:${proc_name} [start(-s) | stop(-t) | restart(-r) | status(-a)" "]"
}
function server_status()
{
	local pid = $(pidof ${BIN_NAME})
	echo ${pid}
}

function server_check()
{
	local ret = $(server_status)
	if [ -z "${ret}" ];then
		echo "${BIN_NAME} doesn't exist!"
	else
		echo "${BIN_NAME} is running,pid is ${pid}"
	fi
}
function server_start()
{
	local ip=$(grep -E '^SERVER_IP' ${CONF} | awk -F ':' '{printf $NF;}')
	local port=$(grep -E '^PORT' ${CONF} | awk -F ':' '{printf $NF;}')
	
	local ret = $(server_status)
	if [ -z ${ret} ];then
		./${BIN_NAME} ${ip} ${PORT}
	else
		echo "${BIN_NAME} has already been started! pid is ${ret}"
		return
	fi

	local ret = $(server_staus)
	if [ -z ${ret} ];then
		echo "failed to start..."
	else
		echo "success to start..."
	fi
}
function Print_Log()
{
	local msg = "$1"
	local level = "$2"
	local time = $(date +%Y_%m_%d:%H:%M:%s)
	echo "${time} ${msg} ${level}">>${LOG}

}
function server_restart()
{
	server_stop
	server_start
}
function server_stop()
{
	local ret = $(server_status)
	if [ -z ${ret} ];then
		echo "${BIN_NAME} hasn't been started..."
		return
	else
		kill -9 ${ret}
	fi

	local ret = $(server_status)
	if [ -z ${ret} ];then
		echo "stop successfully"
	else
		echo "failed to stop..."
	fi	
}

if [ $# -ne 1 ];then 
	Usage
	exit 1
fi

case $1 in
	'start'|'-s' )
	server_start
	;;
	'stop'|'-t' )
	server_stop
	;;
	'restart'|'-r' )
	server_restart
	;;
	'status'|'-a' )
	server_status
	;;
	* )
	Usage
	exit 1
;;
esac




