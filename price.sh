#!/bin/bash
curl -s https://api.coinbase.com/v2/prices/spot?currency=USD | cut -f 5 -d ":" | sed 's/\"//g' | sed 's/}}//' | cut -f 1 -d "." > price.txt
