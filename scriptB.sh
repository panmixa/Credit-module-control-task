#!/bin/bash

# URL сервера
SERVER_URL="http://localhost:80"

# Функція для надсилання запиту
send_request() {
  local delay=$((RANDOM % 6 + 5)) # Випадковий час від 5 до 10 секунд
  while true; do
    RESPONSE=$(curl -s -o /dev/null -w "%{http_code}" "$SERVER_URL")
    if [[ $RESPONSE -eq 200 ]]; then
      echo "[$(date)] Request sent successfully, Response: $RESPONSE" | tee -a scriptB.log
    else
      echo "[$(date)] Request failed, Response: $RESPONSE" | tee -a scriptB.log
    fi
    sleep "$delay"
  done
}

send_request &

