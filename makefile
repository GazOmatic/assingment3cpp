findcomp: PGMimageProcessor.cpp PGMimageProcessor.h ConnectedComponent.cpp
	g++ PGMimageProcessor.cpp -o findcomp -std=c++20

clean:
	rm findcomp