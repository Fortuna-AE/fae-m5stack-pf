idf.py fullclean
idf.py set-target esp32

mkdir -p components
cd components
git clone http://github.com/m5stack/M5GFX.git
git clone http://github.com/m5stack/M5Unified.git
cd ..
