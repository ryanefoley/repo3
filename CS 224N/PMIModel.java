package cs224n.wordaligner;  

import cs224n.util.*;
import java.util.List;

/**
 * Simple word alignment baseline model that maps source positions to target 
 * positions along the diagonal of the alignment grid.
 * 
 * IMPORTANT: Make sure that you read the comments in the
 * cs224n.wordaligner.WordAligner interface.
 * 
 * @author Dan Klein
 * @author Spence Green
 */
public class BaselineWordAligner implements WordAligner {

  private static final long serialVersionUID = 1315751943476440515L;
  
  // TODO: Use arrays or Counters for collecting sufficient statistics
  // from the training data.
  private CounterMap<String,String> sourceTargetCounts;
  private Counter<String> sourceWordCounts;
  private Counter<String> targetWordCounts;

  public Alignment align(SentencePair sentencePair) {
    // Placeholder code below. 
    // TODO Implement an inference algorithm for Eq.1 in the assignment
    // handout to predict alignments based on the counts you collected with train().
    Alignment alignment = new Alignment();
    int numSourceWords = sentencePair.getSourceWords().size();
    int numTargetWords = sentencePair.getTargetWords().size();
    List<String> targetWords = pair.getTargetWords();
    List<String> sourceWords = pair.getSourceWords();
    sourceWords.add(null);
    
    //Get sum of all counts for use in calculating probabilities - want to do this once because recaculates in linear time every time called
    int totalCounts = sourceTargetCounts.totalCounts();
    int totalTgtCount = targetWordCounts.totalCounts();
    int totalSrcCount = sourceWordCounts.totalCounts();
    double new_max = ;0
    //Find alignment that maximizes argument in eq 1 of handout.
    for (int tgtIndex = 0; tgtIndex < numTargetWords; tgtIndex++) {
      String target = targetWords.get(tarIndex);
      for (int srcIndex = 0; srcIndex < numSourceWords; srcIndex++) {
        new_max = (sourceTargetCounts.getCount(source, target)/totalCounts) / ((targetWordCounts.getCount(target) / totalTgtCount) / (sourceWordCounts.getCount(source) / totalSrcCount)); // calculating p(fj,ei)/p(fj)p(ei) for argument in eq 1 from handout
        if(srcIndex == 0){ //initialize max value and best alignment
          double max = new_max;
          int best_aligned_src = srcIndex;
        }
        else{
          if(new_max > max){
            max = new_max;
            best_aligned_src = srcIndex;
          }
        }
      }
      //Assign best alignment found 
      alignment.addPredictedAlignment(tgtIndex, best_aligned_src);
    }
    return alignment;
  }

  public void train(List<SentencePair> trainingPairs) {
    sourceTargetCounts = new CounterMap<String,String>();
    for(SentencePair pair : trainingPairs){
      List<String> targetWords = pair.getTargetWords();
      List<String> sourceWords = pair.getSourceWords();
      for(String source : sourceWords){
        for(String target : targetWords){
          // TODO: Warm-up. Your code here for collecting sufficient statistics.
          sourceTargetCounts.incrementCount(source, target, 1.0);//do I need conditional for if pair not already there or does it automatically start at 0?
          sourceWordCounts.incrementCount(source, 1);
          targetWordCounts.incrementCount(target, 1);
        }
      }
      //Updating appropriate null and target alignment counts for every possible alignment.
      for(String target : targetWords){
        sourceTargetCounts.incrementCount(null, target, targetWords.length());
      }
      //Updating number of null source word counts.
      sourceWordCounts.incrementCount(null, (targetWords.length() * (targetWords.length() - 1)) + 1);
    }
  }
}
