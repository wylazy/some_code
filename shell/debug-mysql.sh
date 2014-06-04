#! /usr/bin/env bash

if [ -f var/mysql.pid ]
then
    echo "mysql.pid exists"
    exit 1
fi

CMD="libexec/mysqld --defaults-file=etc/my.cnf --debug=d,info,error,query,general,where:t:L:g:O,tmp/mysqld.trace"
$CMD &
pid=$!
trap "echo 'kill $pid'; kill $pid" 2 15

while [ 1 ]
do
    kill -0 $pid &> /dev/null

    if [ $? -eq 0  ]
    then
        echo "waiting $pid"
        wait $pid
    else
        break
    fi
done
