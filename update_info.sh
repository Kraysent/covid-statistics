if ! [ -d COVID-19 ]; then
    echo "COVID-19 folder does not exists. Cloning..."
    git clone https://github.com/CSSEGISandData/COVID-19.git
fi

if ! [ -d covid19-russia-data ]; then
    echo "covid19-russia-data folder does not exists. Cloning..."
    git clone https://github.com/k0ka/covid19-russia-data.git
fi

cd COVID-19/
echo "Scanning for changes in COVID-19 folder: "
git pull
cd ../covid19-russia-data
echo "Scanning for changes in covid19-russia-data folder: "
git pull