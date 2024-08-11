#!/bin/bash

ID_FILE=.id
DATA_DIR="../data"

if [[ -f ${ID_FILE} ]]; then
	CONTAINER_ID=`cat ${ID_FILE}`
	echo "Killing container $(cat ${ID_FILE}) ..."
	echo
	docker stop ${CONTAINER_ID} 2>&1 >/dev/null
fi

rm ${DATA_DIR}/id_ed25519_fibonacci*
ssh-keygen -t ed25519 -C "Fibonacci Race Against Time" -N "" -f ${DATA_DIR}/id_ed25519_fibonacci
cp id_ed25519_fibonacci.pub authorized_keys
rm ${DATA_DIR}/ssh_host_ed25519_key*
ssh-keygen -t ed25519 -C "Fibonacci Race Against Time" -N "" -f ${DATA_DIR}/ssh_host_ed25519_key

docker build -t minimal-alpine .
docker run -d --rm -p 2222:22 -v -d minimal-alpine > ${ID_FILE}

echo
echo
echo "Container $(cat ${ID_FILE}) is running."
