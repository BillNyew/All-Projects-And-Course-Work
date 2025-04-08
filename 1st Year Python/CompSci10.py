from nltk.sentiment.vader import SentimentIntensityAnalyzer 
sia = SentimentIntensityAnalyzer()
score = sia.polarity_scores("The ice cream was bad!")
print(score)