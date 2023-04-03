findcomp: driver.cpp PGMimageProcessor.cpp PGMimageProcessor.h ConnectedComponent.cpp ConnectedComponent.h image.h
	g++ driver.cpp -o findcomp -std=c++20

clean:
	rm findcomp; rm heaptrack*;rm out.pgm
