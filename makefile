D_I = include
PROGRAMES = servidor_joc1a1.o 4enRatlla.o f_sockets.o

servidor_joc1a1 : $(PROGRAMES)
	gcc -o  servidor_joc1a1 $(PROGRAMES)
servidor_joc1a1.o : servidor_joc1a1.c $(D_I)/servidor_joc1a1.h $(D_I)/4enRatlla.h $(D_I)/f_sockets.h
	gcc -c $<
4enRatlla.o : 4enRatlla.c $(D_I)/4enRatlla.h
	gcc -c $<
f_sockets.o : f_sockets.c $(D_I)/f_sockets.h
	gcc -c $<
.PHONY : netejar
net :
	$(RM) *.o
