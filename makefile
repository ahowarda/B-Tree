CXX = g++ -std=c++11
m = main
bt = BTree
f = funky
$(bt): $(bt).o $(m).o $ $(f).o
	$(CXX) $(bt).o $(m).o $(f).o -o $(bt)
$(m).o: $(m).cpp $(bt).h $(f).h
	$(CXX) -c $(m).cpp
$(bt).o: $(bt).cpp $(bt).h $(f).h
	$(CXX) -c $(bt).cpp
$(f).o: $(f).cpp $(f).h
		$(CXX) -c $(f).cpp
clean:
	rm -f *.o $(bt)
