#- - - - - - - - - - - - - - - - - - - - 
#Anil P. Singh                              
#Panjab University                       
#Chandigarh                              
#                                        
#This one loops over all the items in     
#your directory and generates code to
#include then in an htmk page.
#
#One can either directly view the output
#file, or cut paste the code segments 
#to include into another html file.
#- - - - - - - - - - - - - - -  - - - - - 


#!usr/bin/python env
import os

pictures = []
names = []
for item in os.listdir('./'):
    file1="%s" %item
    type=file1[-3]+file1[-2]+file1[-1]
    if((type=='gif')or (type=='png') or(type=='jpg')):
           #Generate HTML code
       s1= "<a href =" +'"'+item+'"'+ " target="+ '"_blank">'+"\n"
       s2= "<img src="+'"'+item+'"'+ "width=400 height=400 >"+"\n"
       s3= "</img></a>"+"\n"
       s0=s1+s2+s3+'<br>'##+'<font color="red" size="4">'+item+"</font><br>"
       print "Generating HTML snippet for %s" %(item) 
       pictures.append(s0)
       names.append(file1)

file = open('index.html','w')
file.write('<html>\n')
file.write('\t<head>\n')
file.write('\t</head>\n')
file.write('<body>\n')
file.write('<hr>')
for n in range(0,len(pictures)):
    file.write('<h2><font color="red">\n<u>'+names[n]+'</u>\n</font></h2>\n\n')  
    file.write(pictures[n])
    file.write('<br><br>\n\n\n')
    file.write('<!!!------------------------------->\n')
    
file.write('\t</body>')
file.write('\n</html>')
