- am definit pentru fiecare unitate de timp o constanta care sa tina minte cate unitati imediat mai mici cintine (ex 1 min -> 60 sec), iar pentru luni am facut un vector cu numarul de zile al fiecareia
- am mai definit un vector cu numele lunilor in ordinea lor
- am definit si o constanta START care tine minte anul 1970 (mai exact prima data posibila)

Task 1:
- am declarat o variabila de tip TTime in care am pus valorile pentru ora, minute si secunde calculate tinand cont de faptul ca timestamp contine numarul de secunde incepand cu 1970

Task 2:
- am declarat o variabila tip TDate
- am impartit timestamp la nr de ore dintr-o zi si la nr de secunde dintr-o zi pentru a scapa de valorile in plus (ora, min si sec zilei curente)
- pentru an am adunat la 1970 numarul de ani care reiese din timestamp
- pentru zi si luna am salvat numarul de zile trecute de la inceputul anului curent si am parcurs vectorul cu numzrul de zile ale fiecarei luni, scazand la fiecare pas numarul pentru luna "curenta" pana am ajuns la o valoare posibila pentru o zi a lunii. valoarea lunii este reprezentata de pasul pana la care am putut merge in vectorul cu numarul de zile ale lunilor

Task 3:
- similar cu task-ul anterior
- pentru a tine cont de anii bisecti am impartit perioadele in niste clustere de 4 ani consecutivi in care cel de-al treilea este anul bisect
- astfel am retinut in aux_4years numarul de zile din clusterul care contine data pe care trebuie sa o aflu, in this_4years am calculat in care din cei 4 ani ai cluster-ului este data mea si folosindu-ma de cele doua variabile am calculat anul curent
- pentru zile am luat numarul de zile din cluster, am scazut nr de zile ai anilor anteriori completi din cluster si am verificat daca sunt inainte de "data bisecta" sau nu pentru a vedea daca trebuie sa o scad
- pentru luna si zi am facut ca la task 2

Task 4:
- pentru acest task mi-am facut o functie TimeZone care calculeaza diferenta orara in functie de timezone. in cazul in care ora nou calculata depaseste limitele orare ale unei zile, se aduna/scade o zi din data s.a.m.d pentru luna si an.
- am declarat o variabila de tip TDateTimeTZ si am salvat in variabila difference diferenta de timezone
- in result.time si result.date am pus datele initiale folosind functiile de la task-urile 1 si 3
- am salvat datele care at putea fi modificate si am aplicat asupra lor functia TimeZone. datele nou obtinute le-am pus inapoi in variabila result

Task 5:
- am facut ca la task-ul anterior trecerea din timezone-ul curent in UTC
- am facut operatiile exact inverse de la task-urile 3 si 4 care calculau din timestamp in ora, respectiv data

Task 6:
- am afisat pe rand, in ordinea si formatul cerute, datele legate de data si ora
- in functie de diferenta timezone-ului am afisat + sau - si valoarea diferentei respective

Task 7:
- am alocat un vector de N elemente (pe care la final l-am dezalocat). N este o valoare citita anterior
- deoarece pe fiecare pozitie se regaseste o singura data, am ales sa sortez vectorul crescator inainte de prelucrare, datele ramanand corect sortate in acest mod si dupa calcularea efectiva a datelor
- am parcurs fiecare element al vectorului iar rezultatul prelucrat de functia Task7 l-am salvat intr-o variabila de tip TDate pe care am afisat-o in formatul cerut
- in functia Task7, cu ajutorul functiei BitToInt am salvat pe pozitia corespunzatoare din variabila date de tip TDate, ziua, luna, respectiv anul dat de unsigned int-ul transmis ca parametru
- functia BitToInt are ca parametrii un numar de tip unsigned int x care retine valoarea numarului care trebuie prelucrat, nr_shift care reprezinta cu cate pozitii deplasez spre dreapta bitii lui x astfel incat bitii utili sa fie ultimii si nr_crt care shift-eaza spre stanga bitii lui p (initializat cu 1 pe toate pozitiile bitilor) astfel incat prin negarea lui p sa se faca o masca cu ajutorul careia se poate retine valoarea dorita prin operatorul AND

Task 8:
- pentru acest task am citit N (numarul de date care trebuie extrase)
- am calculat n (numarul de int-uri care trebuiesc citite pentru a putea retine toate cele N date) si am citit cele n valori
- am calculat m (numarul de int-uri necesare pentru calcularea bitilor de control) si am citit m valori
- am alocat un vector in care, folosind functia ControlArrayCalculator am retinut int-urile care retin bitii de control ale datelor citite la inceput
- functia ControlArrayCalculator primeste numarul de int-uri citite si valorile acetora, dar si vectorul in care se retin valorile pentru bitii de control. am parcurs cele n valori din array si am calculat pentru fiecare cati biti cu valoarea 1 contine. am verificat daca numarul bitilor cu 1 este impar si practic am dat valoarea 1 bituluide pe pozitia curenta din vectorul de control
- in acest caz am prelucrat initial vectorul, folosind functia Task8, si apoi l-am sortat in functie de data (deoarece daca l-as fi sortat de la inceput ca la task7 s-ar fi modificat anumite date). am afisat vectorul sortat si am dezalocat toti vectorii folositi
- functia Task8 calculeaza datele tinand cont de asezarea in memorie a valorilor. am un for in care practic parcurg datele (nu int-urile). nr retine numarul de biti folositi pana in momentul respectiv (inclusiv cei care urmeaza a fi prelucrati) iar variabila rand retine in al catelea int ma aflu. cu ajutorul la p parcurg bitii de control. in cazul in care o data are ambele "capete" in acelasi int, verific daca bitii de control ai acelui int sunt egali (in caz negativ, sar peste data respectiva prin continue), in caz contrar verific atat bitul de control al int-ului curent cat si pe cel precedent (practic prin inceperea for-ului de la 1 eu ma aflu mereu la sfarsitul datei curente) (in cazul in care ua dintre aceste egalitati este falsa ma mut in int-ul urmator, crescand variabila rand si sar peste data respectiva). atunci cand bitii de control sunt egali, pentru cazul in care data este in intregime intr-un singur int, aplic un algoritm similar cu functia BitToInt si salvez data in vectorul de date valide (de tip TDate) utilizand functia Task7 de la cerinta anterioara. in cazul in care data se ragaseste in 2 int-uri diferite, calculez cati biti se regasesc in primul int, cati in cel de-al doilea si folosindu-ma de niste masti (cea corespunzatoare pentru primul int avand valorile de 1 shiftate in capatul stang, astfel trebuind a fi shiftate inapoi pe pozitiile din capatul drept pentru a nu se modifica valoarea ceruta) adun la aux cele doua valori aflate si convertesc aux folosind din nou functia Task7

Task 9:
- am citit numarul de timezone-uri si datele acestora intr-un vector de tip TTimezone pe care l-am dezalocat ulterior
- am citit numarul de persoane si datele acestora intr-un vector de structuri tip TPersons (name = numele persoanei, tz_name = numele timezone-ului persoanei, tz_index = index-ul timezoneului persoanei in cadrul vectorului de timezone-uri, nr = numarul de intrevale libere al persoanei, intervals = un vector de tip TInterval unde timestamp = timestamp-ul inceputului unui interval si len = lungimea in ore a intervalului), pe care l-am dezalocat mai tarziu impreuna cu fiecare vector de tip TInterval. deoarece datele din input sunt date in an, luna, zi si ora, le-am citit intr-o variabila auxiliara de tip TDateTimeTZ si apoi le-am converitit in timesamp folosind functia de la Task 5
- am citit in doua variabile datele legate de eveniment
- in functia Planning am declarat doua variabile nr_event = nr de intervale in care se poate organiza evenimentul si index_event = indexul primului interval care indeplineste conditiile cerute (este initial -1 pentru a putea verifica mai tarziu daca s-a gasit un interval valid sau nu). am concatenat intervalele fiecarei persoane dupa cum explic mai jos. am declarat un vector de tip TEventInterval (nr_able = cate persoane pot participa in intervalul respectiv la eveniment, timestamp  = timestampul de incepere al intervalului). am parcurs fiecare persoana, apoi intervalele acestora si am verificat daca timestamp-ul intervalului persoanei coincide cu cel putin unul din cele deja existente in event, iar in caz afirmativ cresteam numarul de persoane care pot participa. in cazul in care niciun interval nu coincide am verificat daca intervalele intermediare de lungimea evenimentului din cadrul intervalului curent al persoanei curente coincide cu un interval din event si din nou cresetam numarul de persoane care pot participa cand era cazul. in cazul in care intervalele nu exista in event, le puneam si facem numarul de persoane care pot participa 1 (persoana curenta). in final am sortat toate intervalele calculate pentru eveniment in functied e timestamp si a, parcurs vectorul event pana cand intalneam un interval la care puteau participa minim cate persoane erau mimim necesare pentru eveniment si salvam index-ul intervalului. in cazul in care index-ul nu se modifica din -1 afisam "imposibil", iar in caz contrar sortam persoanele dupa nume si verificam pentru fiecare interval si subinterval de k ore (unde k este durata evenimentului) daca coincide timestamp-ul cu cel al evenimentului si in caz afirmativ afisam data si ora evenimentului in timezone-ul persoanei. in cazul in care nu coincidea niciun subinterval, am afisat "invalid".
- functia CompressIntervals face din toate intervalele unei persoane, intervale continue (ex daca e un interval de la ora 12 de o ora si unul de la ora 13 de 2 ore, face un interval de la 12 de 3 ore). initial am sortat intervalale in functie de timestamp-urile acestora, apoi am luat o variabila auxiliara de tip interval in care mi-am concatenat pe rand intervalele care sunt de forma mentionata anterior, comparand timestamp-ul primului interval + numarul de ore * 3600 (nr de secunde dintr-o ora) cu timestamp-ul urmatorului interval. in cazul in care cele doua timestamp-uri nu coincideau, verificam daca lungimea intervalului este cel putin cat cea a evenimentului (pentru a nu retine date care sigur sunt nefolositoare), am salvat intervalul in cazul in care indeplinea conditia si am resetat intervalul auxiliar. in final am facut o ultima astfel de comparatie, pentru ultimul interval calculat si am modificat numarul initial de intervale cu numarul de intervale nou obtinute prin concatenare.