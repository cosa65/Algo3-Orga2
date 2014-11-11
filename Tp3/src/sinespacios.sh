for i in {0..3}
do
for j in {1..12}
do
	./tp ../images/img$j\b.bmp out/img$j-$i.bmp $i
done
done
