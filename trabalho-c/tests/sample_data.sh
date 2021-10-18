#!/bin/bash

. helpers.sh

SAVED_DIR=$PWD
TST_DATA_DIR=../tests/data

cd ../data || exit 1

head Vendas_1M.txt >"$TST_DATA_DIR"/Vendas_10.txt
head -n 1000 Vendas_1M.txt >"$TST_DATA_DIR"/Vendas_1k.txt
head -n 50000 Vendas_1M.txt >"$TST_DATA_DIR"/Vendas_50k.txt
head -n 200000 Vendas_1M.txt >"$TST_DATA_DIR"/Vendas_200k.txt

head Clientes.txt >"$TST_DATA_DIR"/Clientes_10.txt
head -n 1000 Clientes.txt >"$TST_DATA_DIR"/Clientes_1k.txt

head Produtos.txt >"$TST_DATA_DIR"/Produtos_10.txt
head -n 1000 Produtos.txt >"$TST_DATA_DIR"/Produtos_1k.txt
head -n 50000 Produtos.txt >"$TST_DATA_DIR"/Produtos_50k.txt

echo_info "Created sample data successfully!"

cd "$SAVED_DIR" || exit 1
