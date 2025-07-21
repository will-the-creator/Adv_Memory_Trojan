#!/bin/bash

git add .
read -p "commit message : " msg
git commit -m "$msg"
echo "message committed..."
git push origin main
echo "updated"