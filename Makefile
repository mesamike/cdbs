all:	clean am.txt

same:	tidy am.txt

am.txt:		main auths.dat call_sign_history.dat	
	./main | sort -n > am.txt

main:	main.c cdbs.c cdbs.h dist.c dist.h
	gcc -g -o main main.c cdbs.c dist.c -lm

auths.dat:	auths ant.dat appl.dat fac.dat appidx.dat facidx.dat
	./auths | sort -n > auths.dat

auths:	auths.c cdbs.c cdbs.h
	gcc -o auths auths.c cdbs.c

ant.dat:	ant am_ant_sys.dat
	./ant > ant.dat

ant:	ant.c  cdbs.c cdbs.h
	gcc -g -o ant ant.c  cdbs.c

am_ant_sys.dat:		am_ant_sys.zip	
	unzip am_ant_sys.zip

am_ant_sys.zip:
	wget ftp://ftp.fcc.gov/pub/Bureaus/MB/Databases/cdbs/am_ant_sys.zip

appl.dat:	app application.dat
	./app > appl.dat

app:	app.c cdbs.c cdbs.h
	gcc -o app app.c cdbs.c

application.dat:	application.zip	
	unzip application.zip

call_sign_history.zip:
	wget https://transition.fcc.gov/ftp/Bureaus/MB/Databases/cdbs/call_sign_history.zip

call_sign_history.dat:	call_sign_history.zip
	unzip call_sign_history.zip

application.zip:
	wget ftp://ftp.fcc.gov/pub/Bureaus/MB/Databases/cdbs/application.zip

fac.dat:	fac facility.dat
	./fac > fac.dat

fac:	fac.c cdbs.c cdbs.h
	gcc -o fac fac.c cdbs.c

facility.dat:		facility.zip
	unzip facility.zip

facility.zip:
	wget ftp://ftp.fcc.gov/pub/Bureaus/MB/Databases/cdbs/facility.zip

appidx.dat:	appidx appl.dat
	./appidx | sort -n  > appidx.dat

appidx:	appidx.c cdbs.c cdbs.h
	gcc -o appidx appidx.c cdbs.c

facidx.dat:	facidx fac.dat
	./facidx | sort -n  > facidx.dat

facidx:	facidx.c cdbs.c cdbs.h
	gcc -o facidx facidx.c cdbs.c

clean:
	rm -f *.dat *.zip

tidy:
	rm -f *.dat

pristine:	clean 
	mv am.txt am.old.txt
	rm -f main ant app fac appidx facidx auths

diff:	clean
	mv am.txt am.old.txt
	make 
	diff am.old.txt am.txt > am.diff.txt

	
