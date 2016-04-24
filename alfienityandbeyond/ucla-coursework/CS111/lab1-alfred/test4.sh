if notcommand
then echo nothing
else echo not a command
fi

sort -u test.sh

bro

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
