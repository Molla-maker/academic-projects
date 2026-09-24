<template>
  <div class="quiz-container">
    <div class="numbers">
      <span v-for="(q, index) in questions" :key="index" 
            :class="{ active: index === currentQuestion, answered: answers[index] !== null }"
            @click="currentQuestion = index">
        {{ index + 1 }}
      </span>
    </div>
    <h2>{{ questions[currentQuestion].text }}</h2>
    <div id="optionsContainer">
      <div v-for="(option, index) in questions[currentQuestion].options" :key="index"
           class="option" :class="getOptionClass(index)" @click="selectAnswer(index)">
        <input type="radio" :name="'answer' + currentQuestion" :value="index" v-model="answers[currentQuestion]">
        {{ option }}
      </div>
    </div>
    <div class="buttons">
      <button v-if="currentQuestion > 0" class="back" @click="currentQuestion--">Назад</button>
      <button class="next" @click="nextQuestion">{{ nextButtonText }}</button>
    </div>
    <div v-if="testCompleted" id="result">Ваш результат: {{ score }}/10 - {{ level }}</div>
  </div>
</template>

<script>
export default {
  data() {
    return {
      questions: [
        { text: "Что такое инерция?", options: ["Свойство сохранять скорость", "Сопротивление движению", "Сила трения"], correct: 0 },
        { text: "Импульс тела (p) выражается формулой:", options: ["p = mv", "p = m/v", "p = v/m"], correct: 0 },
        { text: "Как обозначается ускорение свободного падения?", options: ["g", "a", "v"], correct: 0 },
        { text: "Единица измерения силы", options: ["Ньютон", "Джоуль", "Паскаль"], correct: 0 },
        { text: "Формула для расчёта работы силы", options: ["A = F * s", "A = m * g", "A = p * v"], correct: 0 },
        { text: "Время подъема на максимальную высоту", options: ["v₀/g", "v₀*t", "g*t"], correct: 0 },
        { text: "Какая из формул выражает второй закон Ньютона?", options: ["F = m*a", "F = p*t", "F = v*m"], correct: 0 },
        { text: "Закон сохранения энергии применим в замкнутой системе?", options: ["Да", "Нет"], correct: 0 },
        { text: "Какая формула определяет мощность?", options: ["P = A/t", "P = m*g", "P = F*s"], correct: 0 },
        { text: "Механическая энергия тела складывается из:", options: ["Кинетической и потенциальной", "Электрической и тепловой", "Магнитной и химической"], correct: 0 }
      ],
      currentQuestion: 0,
      answers: Array(10).fill(null),
      testCompleted: false
    };
  },
  computed: {
    nextButtonText() {
      return this.testCompleted ? "Вперёд" : this.allAnswered ? "Завершить" : "Вперёд";
    },
    allAnswered() {
      return this.answers.every(answer => answer !== null);
    },
    score() {
      return this.answers.filter((answer, index) => answer === this.questions[index].correct).length;
    },
    level() {
      return this.score <= 3 ? "Новичок" : this.score <= 6 ? "Любитель" : this.score <= 8 ? "Знаток" : "Учёный";
    }
  },
  methods: {
    selectAnswer(index) {
      this.answers[this.currentQuestion] = index;
    },
    nextQuestion() {
      if (!this.testCompleted && this.allAnswered) {
        this.testCompleted = true;
      } else if (this.currentQuestion < this.questions.length - 1) {
        this.currentQuestion++;
      }
    },
    getOptionClass(index) {
      if (this.testCompleted) {
        if (index === this.questions[this.currentQuestion].correct) return "correct";
        if (index === this.answers[this.currentQuestion] && index !== this.questions[this.currentQuestion].correct) return "wrong";
      }
      return "";
    }
  }
};
</script>

<style scoped>
@import "C:\Users\salty\my-vue-app\physics.css";
</style>