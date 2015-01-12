cd ../ && git clone https://github.com/open-source-parsers/jsoncpp.git && 
cd jsoncpp && mkdir -p build && cd build && cmake .. && make -j && mv lib/libjsoncpp.a ../../mncrft/third-party/lib/;
