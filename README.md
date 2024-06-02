# TradierCPP

TradierCPP is a C++ application designed to interface with the Tradier API, perform market data streaming via WebSockets, and perform custom data processing.

## Features

- **Market Data Streaming:** Utilizes Tradier's WebSocket API to stream real-time market data.
- **Data Processing:** Processes streamed data to perform financial analysis or other operations.
- **Modular Architecture:** Divided into separate modules for streaming and processing to enhance maintainability and scalability.

## Dependencies

- Boost (specifically Asio, Beast, and System components)
- OpenSSL for secure connections
- nlohmann-json for JSON parsing

## Directory Structure

```
TradierCPP/
│
├── include/          - Header files
│   └── Account.h
│   └── EnvReader.h
│   └── EquityOrder.h
│   └── OptionsOrder.h
│   └── Tradier.h
│
├── src/              - Source files
│   ├── Tradier.cpp
│   ├── Account.cpp
│   ├── EnvReader.cpp
│   ├── EquityOrder.cpp
│   ├── OptionsOrder.cpp
│   ├── main.cpp
│   ├── main_stream.cpp
│   ├── main_dataprocess.cpp
│   └── TradierHTTPConnect.cpp
|
├── data/              - Streamed data and processed JSON
│   ├── market_data.txt
│   ├── processed_json{DATE}.txt
│
├── CMakeLists.txt    - CMake build configuration file
└── .env              - Environment variables for API keys and account details
```

## Building the Project

1. **Clone the repository:**

   ```bash
   git clone https://yourrepository.com/TradierCPP.git
   cd TradierCPP
   ```

2. **Build with CMake:**

   ```bash
   mkdir build && cd build
   cmake ..
   make
   ```

   This will generate executable files for different parts of the application, such as for streaming and processing.

## Usage

After building the project, run the executables:

• WebSocket Streaming
```bash
./TradierStream
```

• Convert streamed data into JSON for downstream processing
```bash
./TradierDataProcess
```

• General account information
```bash
./TradierCPP
```

This command will initiate the WebSocket streaming and other financial data processing tasks.

## Configuration

Ensure that the `.env` file is correctly set up with your Tradier API credentials and other configuration details:

```
tradier_acct_live=YourAccountNumber
tradier_token_live=YourAuthToken
```

## Contributing

Still under development, so contributions are welcome. Fork and pull please.

## License

Distributed under the MIT License. See `LICENSE` for more information.

## Contact
```
Tom Hammons
hammons.thomas@gmail.com
https://github.com/thammo4/tradiercpp
```
