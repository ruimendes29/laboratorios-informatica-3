#!/bin/bash

. tests/helpers.sh

DATA_DIR=tests/data
CLS=Clientes
PRD=Produtos
VND=Vendas
RES=0

echo_warning "Testing validation"

./bin/sgv -c $DATA_DIR/$CLS.in -p $DATA_DIR/$PRD.in -v $DATA_DIR/$VND.in -o $DATA_DIR/$CLS.out $DATA_DIR/$PRD.out $DATA_DIR/$VND.out

if test -z "$(diff -q $DATA_DIR/$CLS.test $DATA_DIR/$CLS.out)"; then
  echo_info "Clientes ✓"
else
  echo_error "OUT vs TEST (Clientes):"
  diff -u $DATA_DIR/$CLS.test $DATA_DIR/$CLS.out --color=always
  RES=1
fi

if test -z "$(diff -q $DATA_DIR/$PRD.test $DATA_DIR/$PRD.out)"; then
  echo_info "Produtos ✓"
else
  echo_error "OUT vs TEST (Produtos):"
  diff -u $DATA_DIR/$PRD.test $DATA_DIR/$PRD.out --color=always
  RES=1
fi

if test -z "$(diff -q $DATA_DIR/$VND.test $DATA_DIR/$VND.out)"; then
  echo_info "Vendas ✓"
else
  echo_error "OUT vs TEST (Vendas):"
  diff -u $DATA_DIR/$VND.test $DATA_DIR/$VND.out --color=always
  RES=1
fi

exit $RES
