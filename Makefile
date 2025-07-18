# Make file with rules for project 2 

CMD = g++ -Wall -Wextra -g -O0 -std=c++20

cacheSim : *.cpp
	$(CMD) -o cacheSim cacheSim.cpp

submit : clean # Run the clean target as a pre-req so we only  submit unbuilt files
	tar -cvzf ../proj2.tar.gz ../proj2sol
	@echo Submit ../proj2.tar.gz in Brightspace
	
	
clean : 
	rm -f cacheSim *.o # Add any other files this Makefile created
