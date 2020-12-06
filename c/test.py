import os
#import array

cmd = "~/dev/crawler/c/build/src/bin/crawler_cli --url http://localhost/test.html | wc -m"

i=0
maxrang = 1000
results = []

for line in range(maxrang):
    #print("Launch", i)
    result = os.popen(cmd).read().strip()
    
    if result not in results :
        results.append(result)
        print(result)

    i+=1

