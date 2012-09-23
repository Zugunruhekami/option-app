OBJ=main.o option.o tinyxml.o tinystr.o tinyxmlerror.o tinyxmlparser.o
CPL= g++ -c

main : $(OBJ)
	g++ -o main $(OBJ)

main.o : main.cpp 
	$(CPL) main.cpp

option.o : option.cpp
	$(CPL) option.cpp

tinyxml.o : tinyxml/tinyxml.cpp
	$(CPL) tinyxml/tinyxml.cpp

tinystr.o : tinyxml/tinystr.cpp
	$(CPL) tinyxml/tinystr.cpp

tinyxmlerror.o : tinyxml/tinyxmlerror.cpp 
	$(CPL) tinyxml/tinyxmlerror.cpp

tinyxmlparser.o : tinyxml/tinyxmlparser.cpp
	$(CPL) tinyxml/tinyxmlparser.cpp

.PHONY : clean
clean :
	rm main $(OBJ)

run : 
	./main
main:
