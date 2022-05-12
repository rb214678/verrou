

BIN=stencil

BINO3DOUBLE=$BIN-O3-DOUBLE
BINO0DOUBLE=$BIN-O0-DOUBLE
BINO3FLOAT=$BIN-O3-FLOAT
BINO0FLOAT=$BIN-O0-FLOAT

BINS="./$BINO3DOUBLE ./$BINO0DOUBLE ./$BINO3FLOAT ./$BINO0FLOAT"

OPT="--scale=1 5"



for i in $BINS
do
    echo $i
    $PREFIX $i $OPT

done;
