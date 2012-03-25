all:
	g++ -g -Wall -I/opt/local/include/ -I/opt/local/include/cryptopp -L/opt/local/lib/ -lcryptopp main.cpp package.cpp crypto.cpp -o wcmp
	g++ -g -Wall -I/opt/local/include/ -I/opt/local/include/cryptopp -L/opt/local/lib/ -lcryptopp -lcppunit package.cpp crypto.cpp packageTest.cpp testmain.cpp -o test
