fresh:	clean all

all:	dfac.dat amdb.dat
	make delimited
	$(eval diffstat = $(shell diff amdb.dat amdb.dat.old  2>&1 > /dev/null; echo $$?))
	$(eval diffstat2 = $(shell diff dfac.dat dfac.dat.old  2>&1 > /dev/null; echo $$?))
	@([ ${diffstat} -eq 0 ] && [ ${diffstat2} -eq 0 ] && echo no changes) || (echo some changes; make upload)

delimited:
	date -u "+Last Updated %a, %b %d, %Y at %H%M UTC" > update.txt
	cat update.txt > amdb.txt
	echo "FAC_ID|FREQ|CALL|STATE|COL|PWR_D|PWR_N|PWR_C|LAT|LON|STATUS|CALL_HIST" >> amdb.txt
	cat amdb.dat >> amdb.txt

dfac.dat: dfac facility.dat call_sign_history.dat
	./dfac > dfac.dat
	rm -f dfac_*.idx dfac.dbf

amdb.dat: amdb auths.dat call_sign_history.dat
	./amdb > amdb.tmp
	mv amdb.tmp amdb.dat

auths.dat: auths appidx.dat ant.dat facidx.dat
	./auths | sort -n -k 1,1 -k 2,2  -t '|' > auths.dat

appidx.dat: appidx appl.dat
	./appidx > appidx.dat

facidx.dat: facidx fac.dat
	./facidx > facidx.dat


fac.dat: fac facility.dat
	./fac > fac.dat

ant.dat: ant am_ant_sys.dat
	./ant > ant.dat

appl.dat: app application.dat
	./app > appl.dat

am_ant_sys.dat: am_ant_sys.zip
	unzip am_ant_sys.zip
#	touch am_ant_sys.dat

application.dat: application.zip
	unzip application.zip
#	touch application.dat

facility.dat: facility.zip
	unzip facility.zip
#	touch facility.dat

call_sign_history.dat: call_sign_history.zip
	unzip call_sign_history.zip
#	touch call_sign_history.dat

application.zip:	
	wget ftp://ftp.fcc.gov/pub/Bureaus/MB/Databases/cdbs/application.zip
	
facility.zip:
	wget ftp://ftp.fcc.gov/pub/Bureaus/MB/Databases/cdbs/facility.zip

am_ant_sys.zip:
	wget ftp://ftp.fcc.gov/pub/Bureaus/MB/Databases/cdbs/am_ant_sys.zip

call_sign_history.zip:
	wget ftp://ftp.fcc.gov/pub/Bureaus/MB/Databases/cdbs/call_sign_history.zip

amdb:   amdb.c
	gcc -o amdb amdb.c cdbs.c

antidx: antidx.c cdbs.c cdbs.h
	gcc -o antidx antidx.c cdbs.c

appidx: appidx.c cdbs.c cdbs.h
	gcc -o appidx appidx.c cdbs.c

facidx: facidx.c cdbs.c cdbs.h
	gcc -o facidx facidx.c cdbs.c

ant:    ant.c  cdbs.c cdbs.h
	gcc -g -o ant ant.c  cdbs.c

app:    app.c cdbs.c cdbs.h
	gcc -o app app.c cdbs.c

fac:    fac.c cdbs.c cdbs.h
	gcc -o fac fac.c cdbs.c

dfac:   dfac.c cdbs.c cdbs.h
	gcc -o dfac dfac.c cdbs.c

auths:  auths.c cdbs.c cdbs.h
	gcc -o auths auths.c cdbs.c

clean:
	([ -f amdb.dat ] && mv amdb.dat amdb.dat.old) || touch amdb.dat.old
	([ -f dfac.dat ] && mv dfac.dat dfac.dat.old) || touch dfac.dat.old
	rm -f *.dat *.dbf *.idx *.dbt *.txt *.zip *.log

pristine: clean
	rm -f amdb dfac ant app fac appidx facidx auths *.dat

upload: 
	scp amdb.dat dfac.dat update.txt rebuild gentoo@gentoo.net:~/mivadata/cdbs
	scp amdb.txt gentoo@gentoo.net:~/radio/cdbs/
