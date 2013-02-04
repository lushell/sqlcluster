sqlcluster
==========

Description:
This is a ddbs.
This is a proxy for MySQL/Oracle...

Structure:
1. Listener-> listen tcp port -> 13608.
2. Select poll-> monitor sockect descriptor -> Fetch available descriptor.
3. Linux thread process-> read data into structure from sockect descriptor.
4. Command parse-> parse structure of string-> SQL grammar or other command.
5. Command classification-> SQL grammar -> Hash range -> Search dictionary -> Execute plan.
							Other command -> Execute.
6. Split algorithm-> SQL -> N*SQL.
7. Parallel computing-> Manage data source.
8. Generation results-> Merge data(group by/order by/limit).
9. Send data-> Write to net/client.
