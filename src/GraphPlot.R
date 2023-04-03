runtime = read.csv("C:\\VIT_Resources\\CSE\\Github Repos\\quicksort_time_analysis\\result\\feed.csv")

Sample_Size <- runtime$Sample_Size
Last_Element <- runtime$Last_Element
Middle_Element <- runtime$Middle_Element
Random_Element <- runtime$Random_Element

library(ggplot2)

ggplot(runtime, aes(x = Sample_Size)) +
  geom_line(aes(y = Last_Element, color = "Last_Element", group = 1)) +
  geom_line(aes(y = Middle_Element, color = "Middle_Element", group = 1)) +
  geom_line(aes(y = Random_Element, color = "Random_Element", group = 1)) +
  labs(title = "Element Values by Sample Size", x = "Sample Size", y = "Element Value") +
  scale_color_manual(name = "Element", values = c("Last_Element" = "red", "Middle_Element" = "blue", "Random_Element" = "green"))