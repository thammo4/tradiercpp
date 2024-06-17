import numpy as np
import pandas as pd
import torch
import torch.nn as nn
import torch.optim as optim



#
# Create Limit Order Book
#

# >>> df_clob
#        bidexch             biddate  bidsz     bid     ask  asksz             askdate askexch symbol
# 717          N 2024-04-22 14:32:12    1.0  131.80  131.88    4.0 2024-04-22 14:32:10       N    ICE
# 720          N 2024-04-22 14:32:12    1.0  131.81  131.88    4.0 2024-04-22 14:32:10       N    ICE
# 722          N 2024-04-22 14:32:13    2.0  131.79  131.88    4.0 2024-04-22 14:32:10       N    ICE
# 744          N 2024-04-22 14:32:15    1.0  131.81  131.88    3.0 2024-04-22 14:32:15       N    ICE
# 886          N 2024-04-22 14:32:32    1.0  131.88  131.94    2.0 2024-04-22 14:32:32       N    ICE
# ...        ...                 ...    ...     ...     ...    ...                 ...     ...    ...
# 167881       N 2024-04-22 19:59:57    8.0  131.64  131.67   54.0 2024-04-22 19:59:57       N    ICE
# 167909       N 2024-04-22 19:59:57    9.0  131.64  131.67   46.0 2024-04-22 19:59:58       N    ICE
# 167934       N 2024-04-22 19:59:57    9.0  131.64  131.67   47.0 2024-04-22 19:59:58       N    ICE
# 168029       N 2024-04-22 19:59:59    7.0  131.64  131.65   12.0 2024-04-22 19:59:59       N    ICE
# 168065       N 2024-04-22 19:59:59   43.0  131.63  131.65    8.0 2024-04-22 19:59:59       N    ICE

# [3294 rows x 9 columns]

df_clob = create_clob(file='market_stream_april22.json', symbol='ICE', exchange='N'); print(f'DF CLOB\n{df_clob}');


#
# Convert json file -> Central Limit Order Book
#

def create_clob (file, symbol='', exchange=''):
    stream_data = pd.read_json(file); # print(f'STREAM DATA\n{stream_data.head(10)}\n');
    stream_data = stream_data.query("type == 'quote'")[['bidexch', 'biddate', 'bidsz', 'bid', 'ask', 'asksz', 'askdate', 'askexch', 'symbol']];

    # if symbol is not None:
    if len(symbol) > 0:
        stream_data = stream_data.query("symbol == @symbol");

    # if exchange is not None:
    if len(exchange) > 0:
        stream_data = stream_data.query("bidexch == @exchange");
        stream_data = stream_data.query("askexch == @exchange");

    #
    # Market stream data returns unix timestamps to the millisecond -> Convert to datetime
    #

    stream_data['biddate'] = pd.to_datetime(stream_data['biddate'], unit='ms');
    stream_data['askdate'] = pd.to_datetime(stream_data['askdate'], unit='ms');

    return stream_data;

# Function to calculate Order Flow Imbalance (OFI)
def calculate_ofi(df):
    bid_size = df['bidsz']
    ask_size = df['asksz']
    ofi = bid_size - ask_size
    return ofi

# Function to prepare data for training
def prepare_data(df, window_size):
    X, y = [], []
    for i in range(len(df) - window_size):
        ofi = calculate_ofi(df[i:i+window_size])
        X.append(ofi.values)
        y.append((df.iloc[i+window_size]['bid'] + df.iloc[i+window_size]['ask']) / 2)
    return np.array(X), np.array(y)



# Alpha Extraction Model
class AlphaExtractor(nn.Module):
    def __init__(self, input_size, hidden_size, output_size):
        super(AlphaExtractor, self).__init__()
        self.hidden = nn.Linear(input_size, hidden_size)
        self.output = nn.Linear(hidden_size, output_size)

    def forward(self, x):
        x = torch.relu(self.hidden(x))
        x = self.output(x)
        return x

# Deep Q-Network (DQN)
class DQN(nn.Module):
    def __init__(self, input_size, hidden_size, output_size):
        super(DQN, self).__init__()
        self.hidden = nn.Linear(input_size, hidden_size)
        self.output = nn.Linear(hidden_size, output_size)

    def forward(self, x):
        x = torch.relu(self.hidden(x))
        x = self.output(x)
        return x




# Hyperparameters
input_size = 10
hidden_size = 32
output_size = 6
learning_rate = 0.001
num_episodes = 100
window_size = 10

# Create instances of AlphaExtractor and DQN
alpha_extractor = AlphaExtractor(input_size, hidden_size, output_size)
dqn = DQN(output_size, hidden_size, 2)  # 2 actions: buy or sell

# Loss function and optimizer
criterion = nn.MSELoss()
alpha_optimizer = optim.Adam(alpha_extractor.parameters(), lr=learning_rate)
dqn_optimizer = optim.Adam(dqn.parameters(), lr=learning_rate)

# Training loop
for episode in range(num_episodes):
    # Prepare data for training
    X, y = prepare_data(df_clob, window_size)
    
    # Train AlphaExtractor
    alpha_optimizer.zero_grad()
    alpha_pred = alpha_extractor(torch.FloatTensor(X))
    alpha_loss = criterion(alpha_pred, torch.FloatTensor(y.reshape(-1, 1)))
    alpha_loss.backward()
    alpha_optimizer.step()
    
    # Train DQN
    dqn_optimizer.zero_grad()
    q_values = dqn(alpha_pred.detach())
    q_loss = criterion(q_values, torch.max(q_values, dim=1)[0].unsqueeze(1))
    q_loss.backward()
    dqn_optimizer.step()
    
    # Print loss for every 10 episodes
    if (episode + 1) % 10 == 0:
        print(f"Episode: {episode+1}, Alpha Loss: {alpha_loss.item():.4f}, Q Loss: {q_loss.item():.4f}")



#
# TRAINING OUTPUT
#

# Episode: 10, Alpha Loss: 17300.2754, Q Loss: 0.0228
# Episode: 20, Alpha Loss: 17253.2637, Q Loss: 0.0095
# Episode: 30, Alpha Loss: 17203.5820, Q Loss: 0.0061
# Episode: 40, Alpha Loss: 17146.9551, Q Loss: 0.0028
# Episode: 50, Alpha Loss: 17078.9102, Q Loss: 0.0011
# Episode: 60, Alpha Loss: 16995.3789, Q Loss: 0.0004
# Episode: 70, Alpha Loss: 16893.0273, Q Loss: 0.0003
# Episode: 80, Alpha Loss: 16769.0586, Q Loss: 0.0002
# Episode: 90, Alpha Loss: 16621.2227, Q Loss: 0.0001
# Episode: 100, Alpha Loss: 16448.6113, Q Loss: 0.0001





# Inference
with torch.no_grad():
    ofi_test = calculate_ofi(df_clob[-window_size:])
    alpha_pred_test = alpha_extractor(torch.FloatTensor(ofi_test.values.reshape(1, -1)))
    q_values_test = dqn(alpha_pred_test)
    action = torch.argmax(q_values_test, dim=1).item()
    
    print(f"\nInference:")
    print(f"Predicted Alphas: {alpha_pred_test.numpy().flatten()}")
    print(f"Q-Values: {q_values_test.numpy().flatten()}")
    print(f"Recommended Action: {'Buy' if action == 0 else 'Sell'}")


#
# INFERENCE OUTPUT
#
#
# Inference:
# Predicted Alphas: [46.588326 31.517965 48.260807 38.193485 53.087708 38.552593]
# Q-Values: [-4.6640353 -4.823137 ]
# Recommended Action: Buy