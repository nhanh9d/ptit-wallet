#!/bin/bash
set -e

echo "[LOG] Bắt đầu build project..."
make clean
make

echo "[LOG] Build thành công! Bắt đầu chạy app..."
./build/wallet_app

RESULT=$?
echo "[LOG] Kết thúc chạy app, exit code: $RESULT" 