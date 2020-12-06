import os
#import array

cmd = "~/dev/crawler/c/test/bin/array-test | wc -m"

i=0
maxrang = 1000
results = []

for line in range(maxrang):
    
    result = os.popen(cmd).read().strip()
    
    if result not in results :
        results.append(result)
        print(result)

    i+=1

