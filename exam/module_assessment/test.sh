for i in {0..4}
do
	./a.out < ./ENG/000${i}_in.txt > ./mytest/000${i}.txt
	if diff ./ENG/000${i}_out.txt ./mytest/000${i}.txt
		then echo "CASE ${i} OK"
		else
		echo "CASE ${i} not OK"
	fi
done
