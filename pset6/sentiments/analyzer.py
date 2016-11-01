# encoding: utf8
import nltk
import re
from string import punctuation

class Analyzer():
    """Implements sentiment analysis."""
    posword = []
    negword = []
    regex = re.compile('[%s]' % re.escape(punctuation))

    def __init__(self, positives="positive-words.txt", negatives="negative-words.txt"):
        """Initialize Analyzer."""

        # TODO
        for line in open(negatives):
            if (";" not in line) and line.strip():
                line = line.replace("\n", "")
                self.negword.append(line)
               
        for line in open(positives):
            if (";" not in line) and line.strip():
               line = line.replace("\n", "")
               self.posword.append(line)
           
         

    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""

        # TODO
        score = 0.0
        words = []
        
        oneline = text.replace('\n', ' ')        
        lineWithoutPunctuation = self.regex.sub('', oneline)
        uncasedWords = lineWithoutPunctuation.split()
        
        for word in uncasedWords:
            words.append(word.strip().lower())
         
        for word in words:
            if (word in self.posword):
                score += 1
            elif (word in self.negword):
                score -= 1    
        return score
