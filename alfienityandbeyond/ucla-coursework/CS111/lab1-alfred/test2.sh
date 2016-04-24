if notcommand
then echo nothing
else echo not a command
     fi

echo hello
if ls
then echo ls succeeds
fi
echo hello again

touch file.txt
echo derp > file.txt

echo abc

sort -u test.sh

bro

echo hello
if ls
then echo ls succeeds
fi

while failed
do echo not supposed to happen
done
echo properly failed

until echo a
do echo not supposed to happen
done
echo only echoed a

until cat b
do touch b; echo inside body b
done
rm b

touch a
echo inside body a > a
while cat a; do rm a; done

(ls -a)

echo a; echo b; echo c

cat test.sh | grep w | grep i

if
    if echo first inner condition ; then echo first inner proceed; fi
then

    if echo second inner condition
    then if echo third inner condition; then echo third inner proceed; fi
    fi
    fi

touch outwhile
touch inwhile
echo inside outwhile > outwhile
echo inside inwhile > inwhile
while cat outwhile
do while cat inwhile; do rm inwhile; done
   rm outwhile
done
