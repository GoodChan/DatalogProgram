*.o : *.cpp *.h
	g++ -Wall -Werror -std=c++17 -g *.cpp *.h -o main

main : *.o
	g++ -Wall -Werror -std=c++17 -g *.o -c main

run:
	./main ./testProj2/in50.txt > outm50.txt
	./main ./testProj2/in54.txt > outm54.txt
	./main ./testProj2/in55.txt > outm55.txt
	./main ./testProj2/in56.txt > outm56.txt
	./main ./testProj2/in58.txt > outm58.txt
	./main ./testProj2/in59.txt > outm59.txt
	./main ./testProj2/in61.txt > outm61.txt
	./main ./testProj2/in62.txt > outm62.txt
	./main ./testProj2/in64.txt > outm64.txt
	./main ./testProj2/in88.txt > outm88.txt

check:
	diff -u ./testProj2/out50.txt outm50.txt > diff40.txt
	diff -u ./testProj2/out54.txt outm54.txt > diff44.txt
	diff -u ./testProj2/out55.txt outm55.txt > diff45.txt
	diff -u ./testProj2/out56.txt outm56.txt > diff46.txt
	diff -u ./testProj2/out58.txt outm58.txt > diff47.txt
	diff -u ./testProj2/out59.txt outm59.txt > diff48.txt
	diff -u ./testProj2/out61.txt outm61.txt > diff49.txt
	diff -u ./testProj2/out62.txt outm62.txt > diff54.txt
	diff -u ./testProj2/out64.txt outm64.txt > diff55.txt
	diff -u ./testProj2/out88.txt outm88.txt > diff61.txt

check1:
	gvimdiff -R ./testProj2/out50.txt outm50.txt > diff40.txt
	gvimdiff -R ./testProj2/out54.txt outm54.txt > diff44.txt
	gvimdiff -R ./testProj2/out55.txt outm55.txt > diff45.txt
	gvimdiff -R ./testProj2/out56.txt outm56.txt > diff46.txt
	gvimdiff -R ./testProj2/out58.txt outm58.txt > diff47.txt
	gvimdiff -R ./testProj2/out59.txt outm59.txt > diff48.txt
	gvimdiff -R ./testProj2/out61.txt outm61.txt > diff49.txt
	gvimdiff -R ./testProj2/out62.txt outm62.txt > diff54.txt
	gvimdiff -R ./testProj2/out64.txt outm64.txt > diff55.txt
	gvimdiff -R ./testProj2/out88.txt outm88.txt > diff61.txt

.phony: clean
clean:
	rm main
	rm *outm*
	rm diff*
