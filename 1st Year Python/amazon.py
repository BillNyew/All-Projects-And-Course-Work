import matplotlib.pyplot as plt # pip install matplotlib
from nltk.sentiment.vader import SentimentIntensityAnalyzer # pip install nltk 
import pandas as pd # pip install pandas
import numpy as np
sia = SentimentIntensityAnalyzer()
# using data from kaggle: https://www.kaggle.com/datasets/sid321axn/amazon-alexa-reviews
def get_sentiment(row): # the rows will be sent to this function one at a time
    # TODO: calculate sentiment of review in this row
    review_str = row['verified_review'] # the review (as a string) of this row can be referenced as row['verified_review']
    # whatever is returned will appear in the "positive_score" colum return 0 
    # TODO: return POSITIVE SCORE ONLY
# read csv in, convert it to a pandas dataframe 
# a pandas dataframes, often referred to as a df, is very similar to a table 
df = pd.read_csv("amazon_product_reviews.csv")
# 'head' shows the first 5 rows of a pandas dataframe (df)
# https://pandas.pydata.org/docs/reference/api/pandas.DataFrame.head.html  
print("Original Data Frame: ")
print(df.head())
print('\n') # print newline for readability
# pass each row to "get_sentiment" function (above)
# the return value will be added to the new row in the new "positive_score" column
# https://pandas.pydata.org/docs/reference/api/pandas.DataFrame.apply.html 
df["positive_score"] = df.apply(get_sentiment, axis=1)
print("Data Frame with Sentiment Scores column: ")
print(df.head(10)) # print first 10 rows of df with new positive sentiment score column
print('\n')
# group rows by rating, calculate average positive sentiment score for each rating 
df = df.groupby('rating').agg(average_positive_score=('positive_score', 'mean'))
print(df.head()) # show calculated mean 
# create a simple line plot showing rating vs. average positive sentiment
# https://pandas.pydata.org/docs/reference/api/pandas.DataFrame.plot.html 
df.plot()  # TODO: add a title to the plot
plt.show()