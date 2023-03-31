findcomp: driver.cpp PGMimageProcessor.cpp PGMimageProcessor.h ConnectedComponent.cpp
	g++ driver.cpp -o findcomp -std=c++20

clean:
	rm findcomp;rm driver; rm heaptrack*
