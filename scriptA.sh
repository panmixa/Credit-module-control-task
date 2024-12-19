#!/bin/bash

# Перемінні
CONTAINER_IMAGE="panmixa/httpserver:latest"  # Замініть на ваш образ
RUNNING_INTERVAL=120 # 2 хвилини
CPU_CORES=("0" "1" "2") # CPU для кожного контейнера
CONTAINERS=("srv1" "srv2" "srv3")

# Функція для запуску контейнера на певному ядрі
run_container() {
  local name=$1
  local core=$2
  docker run -d --name "$name" --cpuset-cpus="$core" "$CONTAINER_IMAGE"
}

# Логіка керування контейнерами
while true; do
  for i in {0..2}; do
    container_name=${CONTAINERS[$i]}
    next_container_name=${CONTAINERS[$((i + 1)) % 3]}
    core=${CPU_CORES[$i]}

    # Перевіряємо статус контейнера
    if docker ps -f name="$container_name" --format '{{.Names}}' | grep -q "$container_name"; then
      # Якщо контейнер зайнятий понад 2 хвилини, запускаємо наступний
      if [ "$(docker inspect -f '{{.State.Running}}' "$container_name")" == "true" ]; then
        sleep $RUNNING_INTERVAL
        if docker ps -f name="$next_container_name" --format '{{.Names}}' | grep -q "$next_container_name"; then
          echo "Container $next_container_name is already running."
        else
          echo "Starting $next_container_name on core $core."
          run_container "$next_container_name" "$core"
        fi
      fi
    else
      echo "Container $container_name is not running."
    fi

    # Оновлення контейнерів
    if [ "$(docker images -q "$CONTAINER_IMAGE")" != "$(docker pull "$CONTAINER_IMAGE" | grep Digest)" ]; then
      echo "New image detected. Updating $container_name."
      docker stop "$container_name"
      docker rm "$container_name"
      run_container "$container_name" "$core"
    fi
  done

  sleep 10
done
