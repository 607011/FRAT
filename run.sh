#!/bin/bash

ID_FILE=.id

if [[ -f ${ID_FILE} ]]; then
	CONTAINER_ID=`cat ${ID_FILE}`
	echo "Killing container $(cat ${ID_FILE}) ..."
	echo
	docker stop ${CONTAINER_ID} 2&>1 >/dev/null
fi

docker build -t minimal-alpine .
docker run -d --rm -p 2222:22 -v -d minimal-alpine > ${ID_FILE}

echo
echo
echo "Container $(cat ${ID_FILE}) is running."
