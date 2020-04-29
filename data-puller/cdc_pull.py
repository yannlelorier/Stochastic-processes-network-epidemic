"""
A program to pull information from the
Centers of Disease and Control (CDC)

This example pulls information on COVID-19 related
deaths in the US by county using the socrata API
"""

import pandas as pd
from sodapy import Socrata

client = Socrata("data.cdc.gov", {${secrets.CDC_SECRET_APP}},None)

#accessing the Provisional COVID-19 Death Counts in the United States by County dataset
results = client.get("kn79-hsxy", limit=2000)

results_df = pd.DataFrame.from_records(results)

print(results_df)
