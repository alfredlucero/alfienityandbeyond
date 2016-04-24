#! /bin/sh

tmp=$0-$$.tmp
mkdir "$tmp" || exit

(
cd "$tmp" || exit

cat >test.sh << 'EOF'
echo a

exec echo a

touch file.txt
echo hello > file.txt
cat file.txt | grep hello

cat < file.txt > file2.txt
cat file2.txt

(ls)

touch file3.txt
echo pikachu abc > file3.txt
cat file3.txt | sort -u

if cat file3.txt
then echo file3 succeeded
else echo nothing
fi

if cat empty
then echo echo nothing
else echo empty not a file
fi

while cat file3.txt
do rm file3.txt
done

until cat fake
do touch fake; echo inside body > fake
done

rm fake; rm file.txt; rm file2.txt
EOF

cat >test.exp << 'EOF'
a
hello
hello
file2.txt
file.txt
test.err
test.exp
test.out
test.sh
pikachu abc
pikachu abc
file3 succeeded
empty not a file
pikachu abc
inside body
EOF

../profsh test.sh > test.out 2>test.err || exit

diff -u test.exp test.out || exit
test ! -s test.err || {
    cat test.err
    exit 1
}

) || exit

rm -fr "$tmp"
