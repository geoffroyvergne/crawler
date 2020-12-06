#!/bin/sh

for i in {1..100}
do
    echo "Welcome $i times"
    RESULT=$(~/dev/crawler/c/build/src/bin/crawler_cli --url http://localhost/test.html  | wc -m)

    
    echo $RESULT
done
