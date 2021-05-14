#############################
# General make variables
# ##########################

sourceDir = src

#############################
# C make variables
# ##########################

cHelloSrc = src/C/everybodySayHello.c

#############################
# Final App
# ##########################

finalApp = eveybodySayHello

hello : ${cHelloSrc}
	gcc -o ${finalApp} ${cHelloSrc}

.PHONY : clean
clean :
	rm -rf *.o

.PHONY : purge
purge : clean
	rm -rf ${finalApp}
