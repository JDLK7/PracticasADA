echo "Compilando..."
make

echo "Testeando mapas..."
for ((i=1; i<9; i++)); do
    echo "Mapa " $i

    ./caminante_voraz -p -f mapas/$i.map >> salida.sol
    diff salida.sol soluciones/$i.map.sol
    rm salida.sol
done

echo "Testeando mapa de 1000x1000..."
./caminante_voraz -p -f mapas/big.map >> salida.big.sol
diff -q salida.big.sol soluciones/big.map.sol
rm salida.big.sol

echo "Eliminando ejecutables..."
make clean