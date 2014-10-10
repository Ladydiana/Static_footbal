EGC	-	TEMA 1
		Fotbal static
		Culincu Diana Cristina
		IDE: Visual Studio C++ 2008
		SO: Windows 7



Utilizare - 	Rotit minge:  A, W, D
(taste)		Propulsie minge: S


Functionalitati
		- Exista 2 echipe (blue & orange), fiecare cu poarta specifica
		- Mingea are culoarea rosie. Pt miscare minge vezi Utilizare
		- Scorul e tinut in partea dreapta
		- Cand o echipa a inscris 3 goluri, in partea stanga apare castigatorul (colorat in culoarea echipei care a invins)
		- Dupa castigarea unui joc, timp de cateva secunde in partea stanga apare castigatorul, ceilalti jucatori si mingea dispar,
		apoi jocul se reia automat.


Implementare:	
		- Jucatorii sunt statici si reprezentati prin cercuri. Pt implementarea prin cercuri, am luat un vector a de unghiuri si dupa am calculat puncte dupa formula:
			x=raza*cos(a)
			y=raza*cos(a)
		- Am ales pt usurinta sa pun numai 2 jucatori in fiecare echipa. 
		- Mingea porneste din centru si se da unui jucator random. Pt asta am luat un r=rand()%4 si am facut 4 cazuri separate de propulsie (pt cei 4 jucatori).
		  Miscam mingea folosind translate.
		- Mingea se lipeste de un jucator in momentul in care raza_minge+raza_jucator <=1.2 . Deoarece am ales raza mingii=0.5 si raza jucatorilor=1, initial pusesem in conditie ca suma razelor <=1.5,
		insa am observat ca in anumite cazuri, dupa rotiri consecutive, deoarece compilatorul rotunjea zecimalele, mingea (desi logic trebuia sa fie lipita de jucator), zbura pt ca nu mai indeplinea conditia.
		  Din aceasta cauza, am ales ca suma razelor <=1.2, ca sa evit bug-urile realizate de rotunjiri.
		  Ca sa fie mai usor si cu mai putine if-uri, diferenta dintre coordonate am facut-o folosind modulul fabs.
		  Conditia e verificata atat intre punctele x, cat si intre punctele y.
		  Conditia e verificata atat in onIdle (daca nu e indeplinita mingea se misca dupa politica de sut, sau dupa politica iniala random -depinde de o variabila pe care o modific in cazul in care mingea e in sut),
		cat si in onKey, unde mingea poate fi miscata daca e lipita de jucator.
		- Cand mingea e lipita de un jucator, aceasta poate fi rotita. Pt unghi am folosit PHI din biblioteca math.h si am adaugat #define _USE_MATH_DEFINES
		  Rotim mingea folosind rotateRelativeToPoint(punct_centru_jucator, unghi).
		  Deoarace nu trebuie/nu e nevoie sa stim exact de care jucator e lipita mingea, coordonatele jucatorului le pastram intr-un punct p. E mai usor sa lucram cu el in continuare decat sa facem referinta si if in functie de
		fiecare jucator.
		- Pt propulsia mingii (sutul) am calculat cele doua catete din unghiul pe care mingea il formeaza cu jucatorul, am propulsat mingea intai in functia onKey cu translate(tx, ty) ca sa modificam pozitia
		mingii a.i. sa nu mai fie lipita de jucator, iar apoi in functia onIdle am transmis in continuare acesti tx si ty si am translatat mingea mai usor cu translate(tx/100, ty/100), ca sa vizualizam traiectia
		pe care o are mingea. Mingea poate sa se lipeasca de alt jucator, sa intre in poarte sau sa fie out.
		- In cazul in care mingea e in out, mingea porneste din nou de pe centru si e data random unui alt jucator. (verific out-ul in onIdle in functie de coordonatele terenului)
		- In cazul in care mingea e in poarta, in cazul politicii de autogol, echipa adversa primeste un punct.
		- Atat dupa gol, cat si dupa out, mingea porneste din centru din nou.
		- Fiecare punct de scor are un obiect si un int separat. Int-urile/variabilele (so1, so2, so3, sb1, sb2, sb3) se reseteaza dupa castigarea jocului.
		- Ca sa nu adaugam un obiect de scor de mai multe ori, retinem in variabilele already_marked daca punctul respectiv a fost marcat deja sau nu. Il adaugam numai daca nu.
		- Textul winner (cel maaare cu vreo 50 de puncte) are inital culoarea terenului si apare cand una din echipe castiga.
		  La fel si jucatorii, 'dispar' din teren prin schimbarea culorii.
		  (Am obervat ca daca ii dau remove object si dupa add din nou, obiectele nu se mai adauga a2a oara, asa ca asta a fost solutia cea mai simpla - the user can never know :D )
		- Ca sa arate mai estetic, am scos colorarea axelor obicetelor.


Probleme aparute pe parcurs 
		- Warnings cauzate de float si double. (Am ultilizat float si in headere cerea double.)
		- Am incercat sa folosesc Sleep din windows.h, dupa terminarea unui joc, insa (cel putin la mine pe laptop) se comporta ciudat la modul ca mi se opreste inainte sa faca o animatie pe care o dadusem sa o faca inainte
		de Sleep si de-abia cand porneste din nou imi face animatia respectiva.



Mentiuni	- Am incercat sa fac coding style-ul cat mai placut ochiului, dar e posibil sa-mi fi scapat ceva - am lucrat pe un laptop de 10.1 inches.
		- Textul "WINNER" are 50 de puncte -mi-am dat seama cat de mult e de scris de-abia dupa ce il facusem pe W si am zis ca daca tot l-am facut, sa merg pana la capat