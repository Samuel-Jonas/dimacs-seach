#!/bin/bash

maps=("NY" "BAY" "COL" "FLA" "NW" "NE" "CAL" "LKS" "E" "W" "CTR" "USA")

if [[ "${maps[*]}" =~ (^| )$1($| ) ]]
then
    [[ ! -d data ]] && echo "Creating data directory" && mkdir data

    echo "Downloading coordinates file"
    curl "http://www.diag.uniroma1.it/challenge9/data/USA-road-d/USA-road-d.$1.co.gz" --output "data/$1.co.gz"

    echo "Downloading distances file"
    curl "http://www.diag.uniroma1.it/challenge9/data/USA-road-d/USA-road-d.$1.gr.gz" --output "data/$1.gr.gz"

    echo "Unzipping coordinates file"
    gzip -d "data/$1.co.gz"

    echo "Unzipping distances file"
    gzip -d "data/$1.gr.gz"

    echo "Removing comments from coordinates file"
    sed -i "/^c/d" "data/$1.co"

    echo "Removing comments from distances file"
    sed -i "/^c/d" "data/$1.gr"
else
    echo "Available maps:"
    echo "${maps[*]}"
fi