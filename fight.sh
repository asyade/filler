a=$1;
while [ $a != 0 ]; do
	echo "------------------------";
	./filler_vm -f $2 -p1 $3 -p2 $4 $5 | grep "==";
	a=$((a - 1));
done
